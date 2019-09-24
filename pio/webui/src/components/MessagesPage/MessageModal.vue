<template>
  <div class="modal-card" style="width: auto">
    <b-loading
      :is-full-page="true"
      can-cancel
      :active.sync="isLoading"
    ></b-loading>

    <header class="modal-card-head">
      <p class="modal-card-title" v-if="isNew">Add new message</p>
      <p class="modal-card-title" v-else>Edit message</p>
      <button class="button is-danger" v-if="!isNew" @click="del">
        Delete
      </button>
    </header>
    <section class="modal-card-body">
      <b-field label="Message">
        <b-input
          maxlength="64"
          type="text"
          v-model="newMsg.value"
          placeholder="Your message"
          required
        >
        </b-input>
      </b-field>
      <b-field>
        <b-switch v-model="newMsg.monospace">Monospace</b-switch>
        <b-switch v-model="newMsg.scroll">Enable scroll</b-switch>
      </b-field>
      <b-field label="Save on device">
        <b-select :value="-1" v-model="newMsg.slot">
          <option
            v-for="slot in savedSlots"
            :value="slot.value"
            :key="slot.value"
          >
            {{ slot.label }}
          </option>
        </b-select>
      </b-field>
    </section>
    <footer class="modal-card-foot">
      <button class="button" type="button" @click="$parent.close()">
        Cancel
      </button>
      <button class="button is-primary" @click="save" :disabled="!newMsg.value">
        Save
      </button>
    </footer>
  </div>
</template>

<script>
import { mapMutations, mapState, mapActions } from 'vuex';
import clone from 'lodash/clone';
import pick from 'lodash/pick';

const defaultMsg = {
  value: '',
  monospace: false,
  scroll: true,
  slot: -1,
};

export default {
  props: {
    msg: {
      type: Object,
      default: () => {},
    },
  },
  data() {
    const isNew = !this.msg.value;
    return {
      isLoading: false,
      newMsg: clone(Object.assign({}, defaultMsg, this.msg)),
      isNew,
    };
  },
  computed: {
    ...mapState(['messages', 'deviceSettings']),
    savedSlots() {
      const none = {
        label: 'None',
        value: -1,
      };
      return [
        none,
        ...this.deviceSettings.messages.map((v, i) => ({
          label: `Slot${i + 1} (${v.value})`,
          value: i,
        })),
      ];
    },
  },
  methods: {
    ...mapMutations(['addMessage', 'editMessage', 'deleteMessage']),
    ...mapActions(['postDeviceSettings']),
    async regenerateDeviceSettings() {
      const newDeviceMessages = [1, 2, 3].map((v, i) => {
        const msg = this.messages.find(v => v.slot === i);
        return pick(msg || defaultMsg, ['value', 'monospace', 'scroll']);
      });
      const newDeviceSettings = {
        ...this.deviceSettings,
        messages: newDeviceMessages,
      };
      this.isLoading = true;
      await this.postDeviceSettings(newDeviceSettings);
    },
    async save() {
      const currentSlot = this.msg.slot;
      const newSlot = this.newMsg.slot;
      const isFromSlot = currentSlot > -1;
      const isToSlot = newSlot > -1;
      const prevSlotted = this.messages.find(v => v.slot === newSlot);

      if (this.isNew) {
        this.addMessage(this.newMsg);
      } else {
        this.editMessage({
          oldMsg: this.msg,
          newMsg: this.newMsg,
        });
      }
      if (prevSlotted) {
        // unslot previous msg
        this.editMessage({
          oldMsg: prevSlotted,
          newMsg: clone({ ...prevSlotted, slot: -1 }),
        });
      }

      if (isFromSlot || isToSlot) {
        await this.regenerateDeviceSettings();
      }

      this.$parent.close();
    },
    del() {
      const isFromSlot = this.msg.slot !== -1;
      this.deleteMessage(this.msg);
      if (isFromSlot) {
        this.regenerateDeviceSettings();
      }
      this.$parent.close();
    },
  },
};
</script>
