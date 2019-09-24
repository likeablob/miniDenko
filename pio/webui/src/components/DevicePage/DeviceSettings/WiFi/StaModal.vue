<template>
  <div class="modal-card" style="">
    <b-loading
      :is-full-page="true"
      can-cancel
      :active.sync="isLoading"
    ></b-loading>

    <header class="modal-card-head">
      <p class="modal-card-title">WiFi AP(Client) Setting</p>
    </header>
    <section class="modal-card-body">
      <section class="panel">
        <p class="panel-heading scan-header">
          Scan results
          <b-button
            type="is-primary"
            outlined
            :loading="isScanLoading"
            @click="scan"
            >Rescan</b-button
          >
        </p>
        <a
          :class="{
            'is-active': ap.ssid === deviceSettings.cApName,
          }"
          class="panel-block ap-panel"
          v-for="ap in scanResults"
          :key="ap.ssid"
          @click="onClickAP(ap)"
        >
          <p class="ap-name">{{ ap.ssid }}</p>
          <b-taglist attached>
            <b-tag type="is-dark">Signal Level</b-tag>
            <b-tag :type="signalToLabel(ap.signal)">{{ ap.signal }} / 5</b-tag>
          </b-taglist>
        </a>
        <p
          v-if="!scanResults.length"
          class="panel-block has-text-weight-bold noresult-panel"
        >
          No results
        </p>
      </section>

      <b-field label="SSID">
        <b-input
          maxlength="32"
          type="text"
          v-model="settings.cApName"
          placeholder="SSID"
          validation-message="Only 0-9a-Z_- is allowed"
          pattern="^[0-9a-zA-Z\-_]+$"
          required
        ></b-input>
      </b-field>

      <b-field label="Password">
        <b-input
          type="password"
          v-model="settings.cApPass"
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
      isScanLoading: false,
      settings: {
        cApName: '',
        cApPass: '',
      },
    };
  },
  computed: {
    ...mapState(['deviceSettings', 'scanResults']),
    isValidSSID() {
      return /^[0-9a-zA-Z\-_]+$/.test(this.settings.hApName);
    },
  },
  methods: {
    ...mapActions(['postDeviceSettings', 'fetchScanResults']),
    signalToLabel(v) {
      if (v < 2) {
        return 'is-danger';
      } else if (v < 3) {
        return 'is-warn';
      }
      return 'is-success';
    },
    onClickAP(ap) {
      this.settings.cApName = ap.ssid;
    },
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
    async scan() {
      this.isScanLoading = true;
      await this.fetchScanResults();
      this.isScanLoading = false;
    },
  },
  mounted() {
    this.scan();
    this.settings = pick(this.deviceSettings, ['cApName', 'cApPass']);
  },
};
</script>

<style scoped lang="scss">
.scan-header {
  align-items: center;
  justify-content: space-between;
  display: flex;
}
.ap-panel {
  display: flex;
  flex-wrap: wrap;
  p {
    flex: 1 1 auto;
  }
}
.noresult-panel {
  justify-content: center;
}
</style>
