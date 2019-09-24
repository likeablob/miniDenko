<template>
  <div class="modal-card" style="width: auto">
    <b-loading
      :is-full-page="true"
      can-cancel
      :active.sync="isLoading"
    ></b-loading>

    <header class="modal-card-head">
      <p class="modal-card-title">WiFi AP(Host) Setting</p>
    </header>
    <section class="modal-card-body">
      <b-field label="SSID">
        <b-input
          maxlength="32"
          type="text"
          v-model="settings.hApName"
          placeholder="SSID"
          validation-message="Only 0-9a-Z_- is allowed"
          pattern="^[0-9a-zA-Z\-_]+$"
          required
        ></b-input>
      </b-field>

      <b-field label="Password">
        <b-input
          type="password"
          v-model="settings.hApPass"
          password-reveal
          placeholder="Password"
        ></b-input>
      </b-field>
      <p class="has-text-danger">
        * You have to reboot the device to apply the settings.
      </p>
    </section>
    <footer class="modal-card-foot">
      <b-button @click="$parent.close()">
        Cancel
      </b-button>
      <b-button class="is-primary" @click="save" :disableda="!isValidSSID">
        Save
      </b-button>
    </footer>
  </div>
</template>

<script>
import { mapActions, mapState } from 'vuex';
import pick from 'lodash/pick';

export default {
  data() {
    return {
      isLoading: false,
      settings: {
        hApName: '',
        hApPass: '',
      },
    };
  },
  computed: {
    ...mapState(['deviceSettings']),
    isValidSSID() {
      return /^[0-9a-zA-Z\-_]+$/.test(this.settings.hApName);
    },
  },
  methods: {
    ...mapActions(['postDeviceSettings']),
    async save() {
      console.log(this.settings);
      this.isLoading = true;
      const newSetting = { ...this.deviceSettings, ...this.settings };
      await this.postDeviceSettings(newSetting);
      this.isLoading = false;
      this.$buefy.snackbar.open({
        message: 'You have to reboot the device to apply the settings.',
        type: 'is-warning',
        position: 'is-bottom-right',
        actionText: 'OK',
        indefinite: true,
      });
      this.$parent.close();
    },
  },
  mounted() {
    this.settings = pick(this.deviceSettings, ['hApName', 'hApPass']);
  },
};
</script>
